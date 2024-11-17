/* eslint-disable @typescript-eslint/no-explicit-any */
import type { MetaFunction } from "@remix-run/node";
import { useLoaderData } from "@remix-run/react";
import { Button, PageHeader, Input } from "../components";
import { FaCloudUploadAlt } from "react-icons/fa";
import { useState } from "react";
import { BASE_API_URL } from "../lib/consts";

export const meta: MetaFunction = () => {
  return [
    { title: "HiddenFrame" },
    { name: "description", content: "Welcome to Remix!" },
  ];
};

export async function loader() {
  const resp = await fetch(`${BASE_API_URL}/images`, {
    headers: { Authorization: `Client-ID ${process.env.UNSPLASH_ACCESS_KEY}` },
  });

  if (resp.ok)
    return { photos: await resp.json() };
  else return { photos: [] };
}

export default function Index() {
  const { photos } = useLoaderData<typeof loader>();

  const [loading, setLoading] = useState(false);

  const uploadImage = async (e: React.FormEvent<HTMLFormElement>) => {
    e.preventDefault();
    setLoading(true)

    const formData = new FormData();
    const fileElement = document.getElementById("file") as HTMLInputElement;
    const messageElement = document.getElementById("message") as HTMLInputElement;

    if (!fileElement || !fileElement.files) return;
    const file = fileElement.files[0];
    if (!file) return;

    if (messageElement) formData.append("message", messageElement.value);

    let fileExt: string[] | string = file.name.split(".");
    fileExt = fileExt[fileExt.length - 1];

    formData.append("file", file);
    formData.append("meta", JSON.stringify({
      name: file.name,
      size: file.size,
      ext: fileExt,
    }));


    const resp = await fetch(`${BASE_API_URL}/image/upload`, {
      method: "POST",
      body: formData,
      headers: {
        contentType: "multipart/form-data",
      }
    });

    if (resp.ok) {
      alert("Image uploaded successfully!");
      window.location.reload();
    } else {
      alert("Failed to upload image.");
      setLoading(false)
    }
  }

  return (
    <div className="flex items-center justify-center h-full">
      <div className="flex flex-col items-center gap-16 h-full">
        <PageHeader />

        <form onSubmit={uploadImage} className="flex flex-col gap-2">
          <Input accept=".jpg,.png" id="file" type="file" />
          <Input id="message" type="text" placeholder="Enter message..." />
          <Button loading={loading} type="submit"> <FaCloudUploadAlt className="w-8" /> Upload New Image</Button>
        </form>


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
                {  photo.resolved_payload && <p>{photo.resolved_payload}</p>
                }
              </div>
            ))}
        </div>
      </div>
    </div>
  );
}

