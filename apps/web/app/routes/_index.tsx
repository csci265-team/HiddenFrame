/* eslint-disable @typescript-eslint/no-explicit-any */
import type { MetaFunction, ActionFunction } from "@remix-run/node";
import { json, redirect } from "@remix-run/node";
import { useLoaderData, Form, useNavigation, useActionData } from "@remix-run/react";
import { Button, PageHeader, Input, Switch } from "../components";
import { FaCloudUploadAlt } from "react-icons/fa";
import { useEffect, useState } from "react";
import { BASE_API_URL } from "../lib/consts";
import { toast } from "sonner";

export const meta: MetaFunction = () => {
  return [
    { title: "HiddenFrame" },
    { name: "description", content: "Welcome to HiddenFrame!" },
  ];
};

export async function loader({ request }: { request: Request }) {
  const resp = await fetch(`${BASE_API_URL}/images`, {
    credentials: "include",
    headers: {
      "Content-Type": "application/json",
      "Cookie": request.headers.get("Cookie") || "",
    }
  });

  if (resp.ok)
    return { photos: await resp.json() };
  else {
    resp.json().then(console.error);
    return { photos: [] };
  }
}

export const action: ActionFunction = async ({ request }) => {
  const formData = await request.formData();
  const file = formData.get("file") as File;
  const message = formData.get("message") as string;

  if (!file) {
    return json({ error: "No file uploaded" }, { status: 400 });
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
      contentType: "multipart/form-data",
      "Cookie": request.headers.get("Cookie") || "",
    }
  });

  if (resp.ok) {
    return redirect("/");
  } else {
    return json({ error: "Failed to upload image" }, { status: 500 });
  }
};

export default function Index() {
  const { photos } = useLoaderData<typeof loader>();
  const transition = useNavigation();
  const loading = transition.state === "submitting";
  const [showMessages, setShowMessages] = useState(false);
  const action = useActionData();

  useEffect(() => {
    // @ts-expect-error cant type
    if (action?.error) {
      // @ts-expect-error cant type
      toast.error(action.error || "An error occurred");
    } else {
      toast.success("Image uploaded successfully")
    }
  }, [action]);

  return (
    <div className="flex items-center justify-center h-full">
      <div className="flex flex-col items-center gap-16 h-full">
        <PageHeader />

        <Form method="post" encType="multipart/form-data" className="flex flex-col gap-2">
          <Input accept=".jpg,.png" id="file" name="file" type="file" />
          <Input id="message" name="message" type="text" placeholder="Enter message..." />
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
                <a href={photo.url} target="_blank" rel="noreferrer">
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