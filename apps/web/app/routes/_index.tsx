/* eslint-disable @typescript-eslint/no-explicit-any */
import type { MetaFunction, ActionFunction, LoaderFunction } from "@remix-run/node";
import { json } from "@remix-run/node";
import { useLoaderData, Form, useActionData, useNavigation } from "@remix-run/react";
import { Button, PageHeader, Input, Switch } from "../components";
import { FaCloudUploadAlt } from "react-icons/fa";
import { useState, useEffect } from "react";
import { BASE_API_URL } from "../lib/consts";
import { toast } from "sonner";
import { getSession } from "../session";

export const meta: MetaFunction = () => {
  return [
    { title: "HiddenFrame" },
    { name: "description", content: "Welcome to HiddenFrame!" },
  ];
};

export const loader: LoaderFunction = async ({ request }) => {
  const session = await getSession(request.headers.get("Cookie"));
  const token = session.get("token");
  const username = session.get("username");

  try {
    const resp = await fetch(`${BASE_API_URL}/images`, {
      headers: {
        "Content-Type": "application/json",
        "Authorization": token || "",
        "Cookie": `token=${token}`,
      }
    });

    if (resp.ok)
      return { success: true, message: "", photos: await resp.json(), username };
    else {
      const error = await resp.json();
      console.error(error);
      return { success: false, message: error, photos: [], username };
    }
  } catch (error) {
    return { success: false, message: error, photos: [], username };
  }
};

export const action: ActionFunction = async ({ request }) => {
  const session = await getSession(request.headers.get("Cookie"));
  const token = session.get("token");
  const formData = await request.formData();
  const file = formData.get("file") as File;
  const message = formData.get("message") as string;

  if (!file) {
    return json({ success: false, message: "No file uploaded" }, { status: 400 });
  }

  let fileExt: string[] | string = file.name.split(".");
  fileExt = fileExt[fileExt.length - 1];

  const meta = JSON.stringify({
    name: file.name,
    size: file.size,
    ext: fileExt,
  });

  formData.append("meta", meta);

  if (message && message.length > 0) formData.append("message", message);

  const resp = await fetch(`${BASE_API_URL}/image/upload`, {
    method: "POST",
    body: formData,
    headers: {
      "Authorization": token || "",
      "Cookie": `token=${token}`,
    }
  });

  if (resp.ok) {
    return json({ success: true, message: "Image uploaded successfully" }, { status: 200 });
  } else {
    return json({ success: false, message: "Failed to upload image" }, { status: 500 });
  }
};

type ActionData = {
  success: boolean;
  message: string;
};

export default function Index() {
  const { photos, success: loaderSuccess, message: loaderMessage, username } = useLoaderData<typeof loader>();
  const transition = useNavigation();
  const loading = transition.state === "submitting";
  const action = useActionData<ActionData>();
  const [showMessages, setShowMessages] = useState(false);

  useEffect(() => {
    if (action) {
      if (!action.success) {
        toast.error(action.message || "An error occurred");
      } else {
        toast.success(action.message || "Image uploaded successfully");
      }
    }
  }, [action]);

  useEffect(() => {
    if (!loaderSuccess) {
      toast.error(loaderMessage || "An error occurred");
    }
  }, [loaderSuccess, loaderMessage]);

  return (
    <div className="flex items-center justify-center h-full">
      <div className="flex flex-col items-center gap-16 h-full">
        <PageHeader />


        <Form method="post" encType="multipart/form-data" className="flex flex-col gap-2">
          <Input accept=".jpg,.png" id="file" name="file" type="file" />
          {username && <Input id="message" name="message" type="text" placeholder="Enter message..." />}
          <Button loading={loading} type="submit"> <FaCloudUploadAlt className="w-8" /> Upload New Image</Button>
        </Form>

        <div className="flex items-center space-x-2">
          <Switch id="show-messages" onClick={() => setShowMessages(!showMessages)} />
          <label htmlFor="show-messages">What does this do?</label>
        </div>

        <h2 className="text-2xl font-[Outfit] font-black ">Photos from Unsplash</h2>
        <div className="grid grid-cols-3 gap-4 p-4">
          {photos
            .sort((a: { id: string }, b: { id: string }) => b.id.localeCompare(a.id))
            .map((photo: any) => (
              <div key={photo.id}>
                <a href={`/u/${photo.id}`}>
                  <img className="w-64 h-64 rounded-lg object-cover" src={photo.url} alt="Img loaded from backend" />
                </a>
                {photo.payload && <p>{photo.payload}</p>}
                {showMessages && photo.resolved_payload && <p>{photo.resolved_payload}</p>}
              </div>
            ))}
        </div>
      </div>
    </div>
  );
}